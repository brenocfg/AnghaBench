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
typedef  int /*<<< orphan*/  oggpack_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  oggpack_write ; 
 int /*<<< orphan*/  oggpack_writecopy_helper (int /*<<< orphan*/ *,void*,long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void oggpack_writecopy(oggpack_buffer *b,void *source,long bits){
  oggpack_writecopy_helper(b,source,bits,oggpack_write,0);
}