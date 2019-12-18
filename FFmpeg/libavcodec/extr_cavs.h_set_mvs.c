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
typedef  enum cavs_block { ____Placeholder_cavs_block } cavs_block ;
typedef  int /*<<< orphan*/  cavs_vector ;

/* Variables and functions */
#define  BLK_16X16 130 
#define  BLK_16X8 129 
#define  BLK_8X16 128 
 size_t MV_STRIDE ; 

__attribute__((used)) static inline void set_mvs(cavs_vector *mv, enum cavs_block size) {
    switch(size) {
    case BLK_16X16:
        mv[MV_STRIDE  ] = mv[0];
        mv[MV_STRIDE+1] = mv[0];
    case BLK_16X8:
        mv[1] = mv[0];
        break;
    case BLK_8X16:
        mv[MV_STRIDE] = mv[0];
        break;
    }
}