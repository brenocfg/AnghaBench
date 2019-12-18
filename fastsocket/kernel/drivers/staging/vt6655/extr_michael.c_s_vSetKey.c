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
typedef  int /*<<< orphan*/  VOID ;
typedef  void* DWORD ;

/* Variables and functions */
 void* K0 ; 
 void* K1 ; 
 int /*<<< orphan*/  s_vClear () ; 

__attribute__((used)) static VOID s_vSetKey (DWORD dwK0, DWORD dwK1)
{
    // Set the key
    K0 = dwK0;
    K1 = dwK1;
    // and reset the message
    s_vClear();
}