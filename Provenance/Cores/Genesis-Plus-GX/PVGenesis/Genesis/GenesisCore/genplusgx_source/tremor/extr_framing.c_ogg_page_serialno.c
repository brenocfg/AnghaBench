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
typedef  int /*<<< orphan*/  oggbyte_buffer ;
typedef  int /*<<< orphan*/  ogg_uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  header; } ;
typedef  TYPE_1__ ogg_page ;

/* Variables and functions */
 int /*<<< orphan*/  oggbyte_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oggbyte_read4 (int /*<<< orphan*/ *,int) ; 

ogg_uint32_t ogg_page_serialno(ogg_page *og){
  oggbyte_buffer ob;
  oggbyte_init(&ob,og->header);
  return oggbyte_read4(&ob,14);
}