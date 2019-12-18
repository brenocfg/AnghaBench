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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  fputc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outfile ; 

__attribute__((used)) static void put32(uint32_t v)
{
    fputc( v        & 0xff, outfile);
    fputc((v >>  8) & 0xff, outfile);
    fputc((v >> 16) & 0xff, outfile);
    fputc((v >> 24) & 0xff, outfile);
}