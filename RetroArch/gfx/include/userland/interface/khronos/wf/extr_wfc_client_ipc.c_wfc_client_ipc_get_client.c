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
typedef  int /*<<< orphan*/  WFC_CLIENT_IPC_T ;

/* Variables and functions */
 int /*<<< orphan*/  wfc_client_ipc ; 

WFC_CLIENT_IPC_T *wfc_client_ipc_get_client(void)
{
   return &wfc_client_ipc;
}