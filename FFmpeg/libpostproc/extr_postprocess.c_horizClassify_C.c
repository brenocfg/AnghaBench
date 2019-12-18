#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  QP; } ;
typedef  TYPE_1__ PPContext ;

/* Variables and functions */
 scalar_t__ isHorizDC_C (int /*<<< orphan*/  const*,int,TYPE_1__ const*) ; 
 int isHorizMinMaxOk_C (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int horizClassify_C(const uint8_t src[], int stride, const PPContext *c)
{
    if( isHorizDC_C(src, stride, c) ){
        return isHorizMinMaxOk_C(src, stride, c->QP);
    }else{
        return 2;
    }
}