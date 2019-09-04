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
typedef  int /*<<< orphan*/  X ;
typedef  int /*<<< orphan*/  SSL_PIPE ;
typedef  int /*<<< orphan*/  K ;
typedef  int /*<<< orphan*/  DH_CTX ;

/* Variables and functions */
 int /*<<< orphan*/ * NewSslPipeEx (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

SSL_PIPE *NewSslPipe(bool server_mode, X *x, K *k, DH_CTX *dh)
{
	return NewSslPipeEx(server_mode, x, k, dh, false, NULL);
}