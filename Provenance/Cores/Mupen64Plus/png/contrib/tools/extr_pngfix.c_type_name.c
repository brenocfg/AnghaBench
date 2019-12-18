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
typedef  int png_uint_32 ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  putc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  type_char (int) ; 

__attribute__((used)) static void
type_name(png_uint_32 type, FILE *out)
{
   putc(type_char(type >> 24), out);
   putc(type_char(type >> 16), out);
   putc(type_char(type >>  8), out);
   putc(type_char(type      ), out);
}