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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcpy (void*,int /*<<< orphan*/ ) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uploadthis ; 

__attribute__((used)) static size_t readcallback(void  *ptr,
                           size_t size,
                           size_t nmemb,
                           void *clientp)
{
  int *counter = (int *)clientp;

  if(*counter) {
    /* only do this once and then require a clearing of this */
    fprintf(stderr, "READ ALREADY DONE!\n");
    return 0;
  }
  (*counter)++; /* bump */

  if(size * nmemb > strlen(uploadthis)) {
    fprintf(stderr, "READ!\n");
    strcpy(ptr, uploadthis);
    return strlen(uploadthis);
  }
  fprintf(stderr, "READ NOT FINE!\n");
  return 0;
}