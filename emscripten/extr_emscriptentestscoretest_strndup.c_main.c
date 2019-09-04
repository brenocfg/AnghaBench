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
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* strndup (char const*,int) ; 

int main(int argc, char** argv) {
  const char* source =
      "strndup - duplicate a specific number of bytes from a string";

  char* strdup_val = strndup(source, 0);
  printf("1:%s\n", strdup_val);
  free(strdup_val);

  strdup_val = strndup(source, 7);
  printf("2:%s\n", strdup_val);
  free(strdup_val);

  strdup_val = strndup(source, 1000);
  printf("3:%s\n", strdup_val);
  free(strdup_val);

  strdup_val = strndup(source, 60);
  printf("4:%s\n", strdup_val);
  free(strdup_val);

  strdup_val = strndup(source, 19);
  printf("5:%s\n", strdup_val);
  free(strdup_val);

  strdup_val = strndup(source, -1);
  printf("6:%s\n", strdup_val);
  free(strdup_val);

  return 0;
}