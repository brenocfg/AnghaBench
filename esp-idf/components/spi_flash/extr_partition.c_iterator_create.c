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
typedef  int /*<<< orphan*/  esp_partition_type_t ;
typedef  int /*<<< orphan*/  esp_partition_subtype_t ;
struct TYPE_3__ {char const* label; int /*<<< orphan*/ * info; int /*<<< orphan*/  next_item; int /*<<< orphan*/  subtype; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ esp_partition_iterator_opaque_t ;

/* Variables and functions */
 int /*<<< orphan*/  SLIST_FIRST (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  s_partition_list ; 

__attribute__((used)) static esp_partition_iterator_opaque_t* iterator_create(esp_partition_type_t type,
        esp_partition_subtype_t subtype, const char* label)
{
    esp_partition_iterator_opaque_t* it =
            (esp_partition_iterator_opaque_t*) malloc(sizeof(esp_partition_iterator_opaque_t));
    it->type = type;
    it->subtype = subtype;
    it->label = label;
    it->next_item = SLIST_FIRST(&s_partition_list);
    it->info = NULL;
    return it;
}