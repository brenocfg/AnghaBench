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
struct WriteThis {size_t counter; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (void*,char const*,size_t) ; 
 char** post ; 
 int /*<<< orphan*/  stderr ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static size_t read_callback(void *ptr, size_t size, size_t nmemb, void *userp)
{
  struct WriteThis *pooh = (struct WriteThis *)userp;
  const char *data;

  if(size*nmemb < 1)
    return 0;

  data = post[pooh->counter];

  if(data) {
    size_t len = strlen(data);
    if(size*nmemb < len) {
      fprintf(stderr, "read buffer is too small to run test\n");
      return 0;
    }
    memcpy(ptr, data, len);
    pooh->counter++; /* advance pointer */
    return len;
  }
  return 0;                         /* no more data left to deliver */
}