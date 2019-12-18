#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct callback_data {int output; } ;

/* Variables and functions */
 long CURL_CHUNK_END_FUNC_OK ; 
 int /*<<< orphan*/  fclose (int) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static long file_is_downloaded(struct callback_data *data)
{
  if(data->output) {
    printf("DOWNLOADED\n");
    fclose(data->output);
    data->output = 0x0;
  }
  return CURL_CHUNK_END_FUNC_OK;
}