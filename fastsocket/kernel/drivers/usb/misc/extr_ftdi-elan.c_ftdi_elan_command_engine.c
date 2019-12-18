#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  char u8 ;
struct usb_ftdi {int command_next; int command_head; TYPE_1__* udev; int /*<<< orphan*/  bulk_out_endpointAddr; } ;
struct urb {int /*<<< orphan*/  transfer_dma; int /*<<< orphan*/  transfer_flags; } ;
typedef  int /*<<< orphan*/  diag ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  URB_NO_TRANSFER_DMA_MAP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,...) ; 
 int fill_buffer_with_all_queued_commands (struct usb_ftdi*,char*,int,int) ; 
 int /*<<< orphan*/  ftdi_elan_kick_respond_queue (struct usb_ftdi*) ; 
 int ftdi_elan_total_command_size (struct usb_ftdi*,int) ; 
 int /*<<< orphan*/  ftdi_elan_write_bulk_callback ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* usb_buffer_alloc (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_buffer_free (TYPE_1__*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,TYPE_1__*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,struct usb_ftdi*) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ftdi_elan_command_engine(struct usb_ftdi *ftdi)
{
        int retval;
        char *buf;
        int ed_commands;
        int total_size;
        struct urb *urb;
        int command_size = ftdi->command_next - ftdi->command_head;
        if (command_size == 0)
                return 0;
        total_size = ftdi_elan_total_command_size(ftdi, command_size);
        urb = usb_alloc_urb(0, GFP_KERNEL);
        if (!urb) {
                dev_err(&ftdi->udev->dev, "could not get a urb to write %d comm"
                        "ands totaling %d bytes to the Uxxx\n", command_size,
                        total_size);
                return -ENOMEM;
        }
        buf = usb_buffer_alloc(ftdi->udev, total_size, GFP_KERNEL,
                &urb->transfer_dma);
        if (!buf) {
                dev_err(&ftdi->udev->dev, "could not get a buffer to write %d c"
                        "ommands totaling %d bytes to the Uxxx\n", command_size,
                         total_size);
                usb_free_urb(urb);
                return -ENOMEM;
        }
        ed_commands = fill_buffer_with_all_queued_commands(ftdi, buf,
                command_size, total_size);
        usb_fill_bulk_urb(urb, ftdi->udev, usb_sndbulkpipe(ftdi->udev,
                ftdi->bulk_out_endpointAddr), buf, total_size,
                ftdi_elan_write_bulk_callback, ftdi);
        urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
        if (ed_commands) {
                char diag[40 *3 + 4];
                char *d = diag;
                int m = total_size;
                u8 *c = buf;
                int s = (sizeof(diag) - 1) / 3;
                diag[0] = 0;
                while (s-- > 0 && m-- > 0) {
                        if (s > 0 || m == 0) {
                                d += sprintf(d, " %02X", *c++);
                        } else
                                d += sprintf(d, " ..");
                }
        }
        retval = usb_submit_urb(urb, GFP_KERNEL);
        if (retval) {
                dev_err(&ftdi->udev->dev, "failed %d to submit urb %p to write "
                        "%d commands totaling %d bytes to the Uxxx\n", retval,
                        urb, command_size, total_size);
                usb_buffer_free(ftdi->udev, total_size, buf, urb->transfer_dma);
                usb_free_urb(urb);
                return retval;
        }
        usb_free_urb(urb);        /* release our reference to this urb,
                the USB core will eventually free it entirely */
        ftdi->command_head += command_size;
        ftdi_elan_kick_respond_queue(ftdi);
        return 0;
}