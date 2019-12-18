#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  user_data ;
struct sock {int dummy; } ;
struct iucv_sock {int /*<<< orphan*/  dst_name; int /*<<< orphan*/  src_name; struct iucv_path* path; } ;
struct iucv_path {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* path_sever ) (struct iucv_path*,unsigned char*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASCEBC (unsigned char*,int) ; 
 int /*<<< orphan*/  high_nmcpy (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iucv_path_free (struct iucv_path*) ; 
 struct iucv_sock* iucv_sk (struct sock*) ; 
 int /*<<< orphan*/  low_nmcpy (unsigned char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* pr_iucv ; 
 int /*<<< orphan*/  stub1 (struct iucv_path*,unsigned char*) ; 
 int /*<<< orphan*/  stub2 (struct iucv_path*,unsigned char*) ; 

__attribute__((used)) static void iucv_sever_path(struct sock *sk, int with_user_data)
{
	unsigned char user_data[16];
	struct iucv_sock *iucv = iucv_sk(sk);
	struct iucv_path *path = iucv->path;

	if (iucv->path) {
		iucv->path = NULL;
		if (with_user_data) {
			low_nmcpy(user_data, iucv->src_name);
			high_nmcpy(user_data, iucv->dst_name);
			ASCEBC(user_data, sizeof(user_data));
			pr_iucv->path_sever(path, user_data);
		} else
			pr_iucv->path_sever(path, NULL);
		iucv_path_free(path);
	}
}