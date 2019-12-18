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
typedef  int /*<<< orphan*/  blissbox_pad_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  const* input_autoconfigure_get_blissbox_pad_type_libusb (int,int) ; 
 int /*<<< orphan*/  const* input_autoconfigure_get_blissbox_pad_type_win32 (int,int) ; 

__attribute__((used)) static const blissbox_pad_type_t* input_autoconfigure_get_blissbox_pad_type(int vid, int pid)
{
#if defined(_WIN32)
#if defined(_MSC_VER) || defined(_XBOX)
   /* no MSVC/XBOX support */
   return NULL;
#else
   /* MinGW */
   return input_autoconfigure_get_blissbox_pad_type_win32(vid, pid);
#endif
#else
   return input_autoconfigure_get_blissbox_pad_type_libusb(vid, pid);
#endif
}