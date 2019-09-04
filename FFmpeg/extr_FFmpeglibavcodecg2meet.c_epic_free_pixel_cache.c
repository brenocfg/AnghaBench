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
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* next; } ;
typedef  TYPE_1__ ePICPixListElem ;
struct TYPE_7__ {int* bucket_fill; int* bucket_size; TYPE_4__** bucket; } ;
typedef  TYPE_2__ ePICPixHash ;
struct TYPE_8__ {TYPE_1__* list; } ;

/* Variables and functions */
 int EPIC_HASH_SIZE ; 
 int /*<<< orphan*/  av_free (TYPE_1__*) ; 
 int /*<<< orphan*/  av_freep (TYPE_4__**) ; 

__attribute__((used)) static void epic_free_pixel_cache(ePICPixHash *hash)
{
    int i, j;

    for (i = 0; i < EPIC_HASH_SIZE; i++) {
        for (j = 0; j < hash->bucket_fill[i]; j++) {
            ePICPixListElem *list_elem = hash->bucket[i][j].list;
            while (list_elem) {
                ePICPixListElem *tmp = list_elem->next;
                av_free(list_elem);
                list_elem = tmp;
            }
        }
        av_freep(&hash->bucket[i]);
        hash->bucket_size[i] =
        hash->bucket_fill[i] = 0;
    }
}