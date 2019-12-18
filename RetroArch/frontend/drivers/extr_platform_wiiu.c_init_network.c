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
 int /*<<< orphan*/  ACConnect () ; 
 int /*<<< orphan*/  ACInitialize () ; 
 int /*<<< orphan*/  network_init () ; 
 int /*<<< orphan*/  socket_lib_init () ; 

__attribute__((used)) static void init_network(void)
{
   ACInitialize();
   ACConnect();
#ifdef IS_SALAMANDER
   socket_lib_init();
#else
   network_init();
#endif /* IS_SALAMANDER */
}