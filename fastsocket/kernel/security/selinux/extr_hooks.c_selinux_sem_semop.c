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
typedef  int u32 ;
struct sembuf {int dummy; } ;
struct sem_array {int /*<<< orphan*/  sem_perm; } ;

/* Variables and functions */
 int SEM__READ ; 
 int SEM__WRITE ; 
 int ipc_has_perm (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int selinux_sem_semop(struct sem_array *sma,
			     struct sembuf *sops, unsigned nsops, int alter)
{
	u32 perms;

	if (alter)
		perms = SEM__READ | SEM__WRITE;
	else
		perms = SEM__READ;

	return ipc_has_perm(&sma->sem_perm, perms);
}