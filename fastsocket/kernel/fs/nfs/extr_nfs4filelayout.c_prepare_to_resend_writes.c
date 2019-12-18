#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  verifier; } ;
struct nfs_page {TYPE_3__ wb_verf; } ;
struct TYPE_8__ {int /*<<< orphan*/ * verifier; } ;
struct TYPE_6__ {scalar_t__ tk_status; } ;
struct TYPE_5__ {int /*<<< orphan*/  next; } ;
struct nfs_commit_data {TYPE_4__ verf; TYPE_2__ task; TYPE_1__ pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct nfs_page* nfs_list_entry (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void prepare_to_resend_writes(struct nfs_commit_data *data)
{
	struct nfs_page *first = nfs_list_entry(data->pages.next);

	data->task.tk_status = 0;
	memcpy(data->verf.verifier, first->wb_verf.verifier,
	       sizeof(first->wb_verf.verifier));
	data->verf.verifier[0]++; /* ensure verifier mismatch */
}