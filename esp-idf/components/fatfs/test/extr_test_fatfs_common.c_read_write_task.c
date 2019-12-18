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
typedef  int /*<<< orphan*/  val ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  rval ;
struct TYPE_2__ {size_t word_count; int /*<<< orphan*/  done; void* result; scalar_t__ write; int /*<<< orphan*/  seed; int /*<<< orphan*/  filename; } ;
typedef  TYPE_1__ read_write_test_arg_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 void* ESP_ERR_NOT_FOUND ; 
 void* ESP_FAIL ; 
 void* ESP_OK ; 
 int /*<<< orphan*/  ets_printf (char*,size_t,int,scalar_t__,...) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int fread (scalar_t__*,int,int,int /*<<< orphan*/ *) ; 
 int fwrite (scalar_t__*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ rand () ; 
 int /*<<< orphan*/  srand (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void read_write_task(void* param)
{
    read_write_test_arg_t* args = (read_write_test_arg_t*) param;
    FILE* f = fopen(args->filename, args->write ? "wb" : "rb");
    if (f == NULL) {
        args->result = ESP_ERR_NOT_FOUND;
        goto done;
    }

    srand(args->seed);
    for (size_t i = 0; i < args->word_count; ++i) {
        uint32_t val = rand();
        if (args->write) {
            int cnt = fwrite(&val, sizeof(val), 1, f);
            if (cnt != 1) {
                ets_printf("E(w): i=%d, cnt=%d val=%d\n\n", i, cnt, val);
                args->result = ESP_FAIL;
                goto close;
            }
        } else {
            uint32_t rval;
            int cnt = fread(&rval, sizeof(rval), 1, f);
            if (cnt != 1 || rval != val) {
                ets_printf("E(r): i=%d, cnt=%d rval=%d val=%d\n\n", i, cnt, rval, val);
                args->result = ESP_FAIL;
                goto close;
            }
        }
    }
    args->result = ESP_OK;

close:
    fclose(f);

done:
    xSemaphoreGive(args->done);
    vTaskDelay(1);
    vTaskDelete(NULL);
}