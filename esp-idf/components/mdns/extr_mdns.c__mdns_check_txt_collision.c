#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_4__ {char* key; char* value; struct TYPE_4__* next; } ;
typedef  TYPE_1__ mdns_txt_linked_item_t ;
struct TYPE_5__ {TYPE_1__* txt; } ;
typedef  TYPE_2__ mdns_service_t ;

/* Variables and functions */
 int /*<<< orphan*/  HOOK_MALLOC_FAILED ; 
 int /*<<< orphan*/  _mdns_append_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (scalar_t__) ; 
 int memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int _mdns_check_txt_collision(mdns_service_t * service, const uint8_t * data, size_t len)
{
    size_t data_len = 1;
    if (len == 1 && service->txt) {
        return -1;//we win
    } else if (len > 1 && !service->txt) {
        return 1;//they win
    } else if (len == 1 && !service->txt) {
        return 0;//same
    }

    mdns_txt_linked_item_t * txt = service->txt;
    while (txt) {
        data_len += 2 + strlen(service->txt->key) + strlen(service->txt->value);
        txt = txt->next;
    }

    if (len > data_len) {
        return 1;//they win
    } else if (len < data_len) {
        return -1;//we win
    }

    uint8_t ours[len];
    uint16_t index = 0;
    char * tmp;

    txt = service->txt;
    while (txt) {
        tmp = (char *)malloc(2 + strlen(txt->key) + strlen(txt->value));
        if (tmp) {
            sprintf(tmp, "%s=%s", txt->key, txt->value);
            _mdns_append_string(ours, &index, tmp);
            free(tmp);
        } else {
            HOOK_MALLOC_FAILED;
            // continue
        }
        txt = txt->next;
    }

    int ret = memcmp(ours, data, len);
    if (ret > 0) {
        return -1;//we win
    } else if (ret < 0) {
        return 1;//they win
    }
    return 0;//same
}