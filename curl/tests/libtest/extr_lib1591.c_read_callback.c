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

/* Variables and functions */
 size_t consumed ; 
 int /*<<< orphan*/  data ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,size_t) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t read_callback(void *ptr, size_t size, size_t nmemb, void *stream)
{
  size_t  amount = nmemb * size; /* Total bytes curl wants */

  if(consumed == strlen(data)) {
    return 0;
  }

  if(amount > strlen(data)-consumed) {
    amount = strlen(data);
  }

  consumed += amount;
  (void)stream;
  memcpy(ptr, data, amount);
  return amount;
}