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
 int /*<<< orphan*/  __appInit () ; 
 int /*<<< orphan*/  __libc_init_array () ; 
 int /*<<< orphan*/  __libctru_init (void (*) ()) ; 
 int /*<<< orphan*/  __system_initArgv () ; 

void initSystem(void (*retAddr)(void))
{
   __libctru_init(retAddr);
   __appInit();
   __system_initArgv();
   __libc_init_array();
}