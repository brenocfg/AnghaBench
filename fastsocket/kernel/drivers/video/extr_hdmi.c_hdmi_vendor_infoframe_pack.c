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
typedef  size_t u8 ;
struct hdmi_vendor_infoframe {size_t length; size_t type; size_t version; int /*<<< orphan*/  data; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t ENOSPC ; 
 size_t HDMI_INFOFRAME_HEADER_SIZE ; 
 int /*<<< orphan*/  hdmi_infoframe_checksum (void*,size_t) ; 
 int /*<<< orphan*/  memcpy (size_t*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 

ssize_t hdmi_vendor_infoframe_pack(struct hdmi_vendor_infoframe *frame,
				   void *buffer, size_t size)
{
	u8 *ptr = buffer;
	size_t length;

	length = HDMI_INFOFRAME_HEADER_SIZE + frame->length;

	if (size < length)
		return -ENOSPC;

	memset(buffer, 0, length);

	ptr[0] = frame->type;
	ptr[1] = frame->version;
	ptr[2] = frame->length;
	ptr[3] = 0; /* checksum */

	memcpy(&ptr[HDMI_INFOFRAME_HEADER_SIZE], frame->data, frame->length);

	hdmi_infoframe_checksum(buffer, length);

	return length;
}