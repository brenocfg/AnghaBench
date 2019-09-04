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

/* Variables and functions */
 int CHKMOD ; 

__attribute__((used)) static inline int
plusmod47 (int acc,
           int add)
{
    acc += add;
    if(acc >= CHKMOD)
        acc -= CHKMOD;
    return(acc);
}