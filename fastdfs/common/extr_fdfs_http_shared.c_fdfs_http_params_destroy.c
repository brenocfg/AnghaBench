#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  content_type_hash; scalar_t__ support_multi_range; scalar_t__ need_find_content_type; } ;
typedef  TYPE_1__ FDFSHTTPParams ;

/* Variables and functions */
 int /*<<< orphan*/  hash_destroy (int /*<<< orphan*/ *) ; 

void fdfs_http_params_destroy(FDFSHTTPParams *pParams)
{
	if (!(pParams->need_find_content_type || pParams->support_multi_range))
	{
		hash_destroy(&pParams->content_type_hash);
	}
}