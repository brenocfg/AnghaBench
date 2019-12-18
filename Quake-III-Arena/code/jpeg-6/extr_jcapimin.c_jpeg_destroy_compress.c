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
typedef  scalar_t__ j_compress_ptr ;
typedef  int /*<<< orphan*/  j_common_ptr ;

/* Variables and functions */
 int /*<<< orphan*/  jpeg_destroy (int /*<<< orphan*/ ) ; 

void
jpeg_destroy_compress (j_compress_ptr cinfo)
{
  jpeg_destroy((j_common_ptr) cinfo); /* use common routine */
}