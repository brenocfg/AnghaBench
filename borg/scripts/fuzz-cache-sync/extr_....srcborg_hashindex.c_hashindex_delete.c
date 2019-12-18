#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ num_entries; scalar_t__ lower_limit; int /*<<< orphan*/  num_buckets; } ;
typedef  TYPE_1__ HashIndex ;

/* Variables and functions */
 int /*<<< orphan*/  BUCKET_MARK_DELETED (TYPE_1__*,int) ; 
 int hashindex_lookup (TYPE_1__*,unsigned char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hashindex_resize (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shrink_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hashindex_delete(HashIndex *index, const unsigned char *key)
{
    int idx = hashindex_lookup(index, key, NULL);
    if (idx < 0) {
        return -1;
    }
    BUCKET_MARK_DELETED(index, idx);
    index->num_entries -= 1;
    if(index->num_entries < index->lower_limit) {
        if(!hashindex_resize(index, shrink_size(index->num_buckets))) {
            return 0;
        }
    }
    return 1;
}