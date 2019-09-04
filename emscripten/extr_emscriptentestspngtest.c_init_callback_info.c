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
typedef  int /*<<< orphan*/  png_const_infop ;
struct TYPE_3__ {int /*<<< orphan*/  info_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEMZERO (TYPE_1__) ; 
 TYPE_1__ user_chunk_data ; 

__attribute__((used)) static void
init_callback_info(png_const_infop info_ptr)
{
   MEMZERO(user_chunk_data);
   user_chunk_data.info_ptr = info_ptr;
}