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

/* Variables and functions */
 int /*<<< orphan*/  fputc (long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sndoutput ; 

__attribute__((used)) static void write32(long x)
{
	fputc(x & 0xff, sndoutput);
	fputc((x >> 8) & 0xff, sndoutput);
	fputc((x >> 16) & 0xff, sndoutput);
	fputc((x >> 24) & 0xff, sndoutput);
}