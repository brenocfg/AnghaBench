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
typedef  int __u32 ;

/* Variables and functions */
 int D_CONF ; 
 int D_STREAM ; 
 int /*<<< orphan*/  PDEBUG (int,char*,char*,int,int,int,...) ; 

__attribute__((used)) static void PDEBUG_MODE(char *txt, __u32 pixfmt, int w, int h)
{
	if ((pixfmt >> 24) >= '0' && (pixfmt >> 24) <= 'z') {
		PDEBUG(D_CONF|D_STREAM, "%s %c%c%c%c %dx%d",
			txt,
			pixfmt & 0xff,
			(pixfmt >> 8) & 0xff,
			(pixfmt >> 16) & 0xff,
			pixfmt >> 24,
			w, h);
	} else {
		PDEBUG(D_CONF|D_STREAM, "%s 0x%08x %dx%d",
			txt,
			pixfmt,
			w, h);
	}
}