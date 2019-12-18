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
struct TYPE_2__ {int remains; scalar_t__ print_content; } ;
typedef  TYPE_1__ chunk_data_t ;

/* Variables and functions */
 long CURL_CHUNK_END_FUNC_OK ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static
long chunk_end(void *ptr)
{
  chunk_data_t *ch_d = ptr;
  if(ch_d->print_content) {
    ch_d->print_content = 0;
    printf("-------------------------------------------------------------\n");
  }
  if(ch_d->remains == 1)
    printf("=============================================================\n");
  return CURL_CHUNK_END_FUNC_OK;
}