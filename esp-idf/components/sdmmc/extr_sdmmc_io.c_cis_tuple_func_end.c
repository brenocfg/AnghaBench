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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_2__ {char* name; } ;
typedef  TYPE_1__ cis_tuple_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static esp_err_t cis_tuple_func_end(const void* p, uint8_t* data, FILE* fp)
{
    const cis_tuple_t* tuple = (const cis_tuple_t*)p;
    data++;
    fprintf(fp, "TUPLE: %s\n", tuple->name);
    return ESP_OK;
}