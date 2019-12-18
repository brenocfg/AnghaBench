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
struct TYPE_6__ {unsigned char const* buckets; int bucket_size; int num_buckets; } ;
typedef  TYPE_1__ HashIndex ;

/* Variables and functions */
 unsigned char* BUCKET_ADDR (TYPE_1__*,int) ; 
 scalar_t__ BUCKET_IS_DELETED (TYPE_1__*,int) ; 
 scalar_t__ BUCKET_IS_EMPTY (TYPE_1__*,int) ; 

__attribute__((used)) static unsigned char *
hashindex_next_key(HashIndex *index, const unsigned char *key)
{
    int idx = 0;
    if(key) {
        idx = 1 + (key - index->buckets) / index->bucket_size;
    }
    if (idx == index->num_buckets) {
        return NULL;
    }
    while(BUCKET_IS_EMPTY(index, idx) || BUCKET_IS_DELETED(index, idx)) {
        idx ++;
        if (idx == index->num_buckets) {
            return NULL;
        }
    }
    return BUCKET_ADDR(index, idx);
}