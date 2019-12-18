#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  png_const_bytep ;
typedef  int /*<<< orphan*/  png_alloc_size_t ;
struct TYPE_3__ {scalar_t__ output_len; int /*<<< orphan*/  input_len; int /*<<< orphan*/  input; } ;
typedef  TYPE_1__ compression_state ;

/* Variables and functions */

__attribute__((used)) static void
png_text_compress_init(compression_state *comp, png_const_bytep input,
    png_alloc_size_t input_len)
{
   comp->input = input;
   comp->input_len = input_len;
   comp->output_len = 0;
}