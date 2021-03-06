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
typedef  int __int64 ;

/* Variables and functions */
 int _InterlockedAnd64 (int volatile*,int) ; 

__int64 interlocked_and_fetch_64(__int64 volatile* ptr, __int64 val) {
  return _InterlockedAnd64(ptr, val) & val;
}