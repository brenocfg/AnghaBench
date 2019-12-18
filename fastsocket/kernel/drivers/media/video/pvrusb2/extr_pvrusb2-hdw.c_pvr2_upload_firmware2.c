#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct pvr2_hdw {TYPE_1__* hdw_desc; int /*<<< orphan*/  usb_dev; scalar_t__ state_encoder_runok; int /*<<< orphan*/  encoder_run_timer; scalar_t__ enc_cur_valid; } ;
struct firmware {unsigned int size; scalar_t__ data; } ;
struct TYPE_2__ {scalar_t__ signal_routing_scheme; scalar_t__ flag_skip_cx23416_firmware; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char const**) ; 
#define  CX2341X_FIRM_ENC_FILENAME 128 
 int EINVAL ; 
 int ENOMEM ; 
 unsigned int FIRMWARE_CHUNK_SIZE ; 
 int FX2CMD_FWPOST1 ; 
 int FX2CMD_MEMSEL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  PVR2_FIRMWARE_ENDPOINT ; 
 scalar_t__ PVR2_ROUTING_SCHEME_GOTVIEW ; 
 int /*<<< orphan*/  PVR2_TRACE_ERROR_LEGS ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,scalar_t__,unsigned int) ; 
 int pvr2_hdw_cmd_deep_reset (struct pvr2_hdw*) ; 
 int pvr2_hdw_gpio_chg_dir (struct pvr2_hdw*,int,int) ; 
 int pvr2_hdw_gpio_chg_out (struct pvr2_hdw*,int,int) ; 
 int pvr2_issue_simple_cmd (struct pvr2_hdw*,int) ; 
 int pvr2_locate_firmware (struct pvr2_hdw*,struct firmware const**,char*,int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*,...) ; 
 int pvr2_write_register (struct pvr2_hdw*,int,int) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int /*<<< orphan*/  swab32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_firmware (char*,...) ; 
 int /*<<< orphan*/  trace_stbit (char*,scalar_t__) ; 
 int usb_bulk_msg (int /*<<< orphan*/ ,unsigned int,void*,unsigned int,int*,int /*<<< orphan*/ ) ; 
 unsigned int usb_sndbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int pvr2_upload_firmware2(struct pvr2_hdw *hdw)
{
	const struct firmware *fw_entry = NULL;
	void  *fw_ptr;
	unsigned int pipe, fw_len, fw_done, bcnt, icnt;
	int actual_length;
	int ret = 0;
	int fwidx;
	static const char *fw_files[] = {
		CX2341X_FIRM_ENC_FILENAME,
	};

	if (hdw->hdw_desc->flag_skip_cx23416_firmware) {
		return 0;
	}

	trace_firmware("pvr2_upload_firmware2");

	ret = pvr2_locate_firmware(hdw,&fw_entry,"encoder",
				   ARRAY_SIZE(fw_files), fw_files);
	if (ret < 0) return ret;
	fwidx = ret;
	ret = 0;
	/* Since we're about to completely reinitialize the encoder,
	   invalidate our cached copy of its configuration state.  Next
	   time we configure the encoder, then we'll fully configure it. */
	hdw->enc_cur_valid = 0;

	/* Encoder is about to be reset so note that as far as we're
	   concerned now, the encoder has never been run. */
	del_timer_sync(&hdw->encoder_run_timer);
	if (hdw->state_encoder_runok) {
		hdw->state_encoder_runok = 0;
		trace_stbit("state_encoder_runok",hdw->state_encoder_runok);
	}

	/* First prepare firmware loading */
	ret |= pvr2_write_register(hdw, 0x0048, 0xffffffff); /*interrupt mask*/
	ret |= pvr2_hdw_gpio_chg_dir(hdw,0xffffffff,0x00000088); /*gpio dir*/
	ret |= pvr2_hdw_gpio_chg_out(hdw,0xffffffff,0x00000008); /*gpio output state*/
	ret |= pvr2_hdw_cmd_deep_reset(hdw);
	ret |= pvr2_write_register(hdw, 0xa064, 0x00000000); /*APU command*/
	ret |= pvr2_hdw_gpio_chg_dir(hdw,0xffffffff,0x00000408); /*gpio dir*/
	ret |= pvr2_hdw_gpio_chg_out(hdw,0xffffffff,0x00000008); /*gpio output state*/
	ret |= pvr2_write_register(hdw, 0x9058, 0xffffffed); /*VPU ctrl*/
	ret |= pvr2_write_register(hdw, 0x9054, 0xfffffffd); /*reset hw blocks*/
	ret |= pvr2_write_register(hdw, 0x07f8, 0x80000800); /*encoder SDRAM refresh*/
	ret |= pvr2_write_register(hdw, 0x07fc, 0x0000001a); /*encoder SDRAM pre-charge*/
	ret |= pvr2_write_register(hdw, 0x0700, 0x00000000); /*I2C clock*/
	ret |= pvr2_write_register(hdw, 0xaa00, 0x00000000); /*unknown*/
	ret |= pvr2_write_register(hdw, 0xaa04, 0x00057810); /*unknown*/
	ret |= pvr2_write_register(hdw, 0xaa10, 0x00148500); /*unknown*/
	ret |= pvr2_write_register(hdw, 0xaa18, 0x00840000); /*unknown*/
	ret |= pvr2_issue_simple_cmd(hdw,FX2CMD_FWPOST1);
	ret |= pvr2_issue_simple_cmd(hdw,FX2CMD_MEMSEL | (1 << 8) | (0 << 16));

	if (ret) {
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "firmware2 upload prep failed, ret=%d",ret);
		release_firmware(fw_entry);
		goto done;
	}

	/* Now send firmware */

	fw_len = fw_entry->size;

	if (fw_len % sizeof(u32)) {
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "size of %s firmware"
			   " must be a multiple of %zu bytes",
			   fw_files[fwidx],sizeof(u32));
		release_firmware(fw_entry);
		ret = -EINVAL;
		goto done;
	}

	fw_ptr = kmalloc(FIRMWARE_CHUNK_SIZE, GFP_KERNEL);
	if (fw_ptr == NULL){
		release_firmware(fw_entry);
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "failed to allocate memory for firmware2 upload");
		ret = -ENOMEM;
		goto done;
	}

	pipe = usb_sndbulkpipe(hdw->usb_dev, PVR2_FIRMWARE_ENDPOINT);

	fw_done = 0;
	for (fw_done = 0; fw_done < fw_len;) {
		bcnt = fw_len - fw_done;
		if (bcnt > FIRMWARE_CHUNK_SIZE) bcnt = FIRMWARE_CHUNK_SIZE;
		memcpy(fw_ptr, fw_entry->data + fw_done, bcnt);
		/* Usbsnoop log shows that we must swap bytes... */
		/* Some background info: The data being swapped here is a
		   firmware image destined for the mpeg encoder chip that
		   lives at the other end of a USB endpoint.  The encoder
		   chip always talks in 32 bit chunks and its storage is
		   organized into 32 bit words.  However from the file
		   system to the encoder chip everything is purely a byte
		   stream.  The firmware file's contents are always 32 bit
		   swapped from what the encoder expects.  Thus the need
		   always exists to swap the bytes regardless of the endian
		   type of the host processor and therefore swab32() makes
		   the most sense. */
		for (icnt = 0; icnt < bcnt/4 ; icnt++)
			((u32 *)fw_ptr)[icnt] = swab32(((u32 *)fw_ptr)[icnt]);

		ret |= usb_bulk_msg(hdw->usb_dev, pipe, fw_ptr,bcnt,
				    &actual_length, HZ);
		ret |= (actual_length != bcnt);
		if (ret) break;
		fw_done += bcnt;
	}

	trace_firmware("upload of %s : %i / %i ",
		       fw_files[fwidx],fw_done,fw_len);

	kfree(fw_ptr);
	release_firmware(fw_entry);

	if (ret) {
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "firmware2 upload transfer failure");
		goto done;
	}

	/* Finish upload */

	ret |= pvr2_write_register(hdw, 0x9054, 0xffffffff); /*reset hw blocks*/
	ret |= pvr2_write_register(hdw, 0x9058, 0xffffffe8); /*VPU ctrl*/
	ret |= pvr2_issue_simple_cmd(hdw,FX2CMD_MEMSEL | (1 << 8) | (0 << 16));

	if (ret) {
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "firmware2 upload post-proc failure");
	}

 done:
	if (hdw->hdw_desc->signal_routing_scheme ==
	    PVR2_ROUTING_SCHEME_GOTVIEW) {
		/* Ensure that GPIO 11 is set to output for GOTVIEW
		   hardware. */
		pvr2_hdw_gpio_chg_dir(hdw,(1 << 11),~0);
	}
	return ret;
}