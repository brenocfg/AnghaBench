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
typedef  int /*<<< orphan*/  nvs_type_t ;
typedef  int /*<<< orphan*/ * nvs_iterator_t ;
struct TYPE_3__ {char* namespace_name; char* key; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ nvs_entry_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/ * nvs_entry_find (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvs_entry_info (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * nvs_entry_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  str_to_type (char const*) ; 
 char* type_to_str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int list(const char *part, const char *name, const char *str_type)
{
    nvs_type_t type = str_to_type(str_type);

    nvs_iterator_t it = nvs_entry_find(part, NULL, type);
    if (it == NULL) {
        ESP_LOGE(TAG, "No such enty was found");
        return 1;
    }

    do {
        nvs_entry_info_t info;
        nvs_entry_info(it, &info);
        it = nvs_entry_next(it);

        printf("namespace '%s', key '%s', type '%s' \n",
               info.namespace_name, info.key, type_to_str(info.type));
    } while (it != NULL);

    return 0;
}