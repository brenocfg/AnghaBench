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
struct TYPE_3__ {int storage; int endbyte; int endbit; } ;
typedef  TYPE_1__ qr_pack_buf ;

/* Variables and functions */

__attribute__((used)) static int qr_pack_buf_avail(const qr_pack_buf *_b){
  return (_b->storage-_b->endbyte<<3)-_b->endbit;
}