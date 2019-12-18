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
typedef  int /*<<< orphan*/  CMSampleBufferRef ;
typedef  int /*<<< orphan*/  CFIndex ;
typedef  int /*<<< orphan*/  CFDictionaryRef ;
typedef  int /*<<< orphan*/  CFBooleanRef ;
typedef  int /*<<< orphan*/  CFArrayRef ;

/* Variables and functions */
 int /*<<< orphan*/  CFArrayGetCount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFArrayGetValueAtIndex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFBooleanGetValue (int /*<<< orphan*/ ) ; 
 scalar_t__ CFDictionaryGetValueIfPresent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const**) ; 
 int /*<<< orphan*/  CMSampleBufferGetSampleAttachmentsArray (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kCMSampleAttachmentKey_NotSync ; 

__attribute__((used)) static void vtenc_get_frame_info(CMSampleBufferRef buffer, bool *is_key_frame)
{
    CFArrayRef      attachments;
    CFDictionaryRef attachment;
    CFBooleanRef    not_sync;
    CFIndex         len;

    attachments = CMSampleBufferGetSampleAttachmentsArray(buffer, false);
    len = !attachments ? 0 : CFArrayGetCount(attachments);

    if (!len) {
        *is_key_frame = true;
        return;
    }

    attachment = CFArrayGetValueAtIndex(attachments, 0);

    if (CFDictionaryGetValueIfPresent(attachment,
                                      kCMSampleAttachmentKey_NotSync,
                                      (const void **)&not_sync))
    {
        *is_key_frame = !CFBooleanGetValue(not_sync);
    } else {
        *is_key_frame = true;
    }
}