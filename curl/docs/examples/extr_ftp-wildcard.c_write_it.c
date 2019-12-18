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
struct callback_data {scalar_t__ output; } ;

/* Variables and functions */
 size_t fwrite (char*,size_t,size_t,scalar_t__) ; 
 scalar_t__ stdout ; 

__attribute__((used)) static size_t write_it(char *buff, size_t size, size_t nmemb,
                       void *cb_data)
{
  struct callback_data *data = cb_data;
  size_t written = 0;
  if(data->output)
    written = fwrite(buff, size, nmemb, data->output);
  else
    /* listing output */
    written = fwrite(buff, size, nmemb, stdout);
  return written;
}