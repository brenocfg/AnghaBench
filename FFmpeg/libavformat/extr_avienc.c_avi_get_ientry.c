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
struct TYPE_3__ {int /*<<< orphan*/ ** cluster; } ;
typedef  TYPE_1__ AVIIndex ;
typedef  int /*<<< orphan*/  AVIIentry ;

/* Variables and functions */
 int AVI_INDEX_CLUSTER_SIZE ; 

__attribute__((used)) static inline AVIIentry *avi_get_ientry(const AVIIndex *idx, int ent_id)
{
    int cl = ent_id / AVI_INDEX_CLUSTER_SIZE;
    int id = ent_id % AVI_INDEX_CLUSTER_SIZE;
    return &idx->cluster[cl][id];
}