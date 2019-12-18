#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u32 ;

/* Variables and functions */
 unsigned long EFAULT ; 
 scalar_t__ HCI_SUCCESS ; 
 int /*<<< orphan*/  HCI_VIDEO_OUT ; 
 int /*<<< orphan*/  HCI_VIDEO_OUT_CRT ; 
 int /*<<< orphan*/  HCI_VIDEO_OUT_LCD ; 
 int /*<<< orphan*/  HCI_VIDEO_OUT_TV ; 
 int /*<<< orphan*/  METHOD_VIDEO_OUT ; 
 int /*<<< orphan*/  _set_bit (unsigned int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hci_read1 (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 int sscanf (char const*,char*,int*) ; 
 int /*<<< orphan*/  write_acpi_int (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static unsigned long write_video(const char *buffer, unsigned long count)
{
	int value;
	int remain = count;
	int lcd_out = -1;
	int crt_out = -1;
	int tv_out = -1;
	u32 hci_result;
	u32 video_out;

	/* scan expression.  Multiple expressions may be delimited with ;
	 *
	 *  NOTE: to keep scanning simple, invalid fields are ignored
	 */
	while (remain) {
		if (sscanf(buffer, " lcd_out : %i", &value) == 1)
			lcd_out = value & 1;
		else if (sscanf(buffer, " crt_out : %i", &value) == 1)
			crt_out = value & 1;
		else if (sscanf(buffer, " tv_out : %i", &value) == 1)
			tv_out = value & 1;
		/* advance to one character past the next ; */
		do {
			++buffer;
			--remain;
		}
		while (remain && *(buffer - 1) != ';');
	}

	hci_read1(HCI_VIDEO_OUT, &video_out, &hci_result);
	if (hci_result == HCI_SUCCESS) {
		unsigned int new_video_out = video_out;
		if (lcd_out != -1)
			_set_bit(&new_video_out, HCI_VIDEO_OUT_LCD, lcd_out);
		if (crt_out != -1)
			_set_bit(&new_video_out, HCI_VIDEO_OUT_CRT, crt_out);
		if (tv_out != -1)
			_set_bit(&new_video_out, HCI_VIDEO_OUT_TV, tv_out);
		/* To avoid unnecessary video disruption, only write the new
		 * video setting if something changed. */
		if (new_video_out != video_out)
			write_acpi_int(METHOD_VIDEO_OUT, new_video_out);
	} else {
		return -EFAULT;
	}

	return count;
}