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
typedef  int int64_t ;

/* Variables and functions */
 int ccv_cache_generate_signature (char*,int,int,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

int main(int argc, char **argv) {
  argv[0] = (char*)"...";
  for (int i = 0; i < argc; i++) {
    int64_t x;
    if (i % 123123 == 0)
      x = ccv_cache_generate_signature(argv[i], i + 2, (int64_t)argc * argc,
                                       54.111);
    else
      x = ccv_cache_generate_signature(argv[i], i + 2, (int64_t)argc * argc,
                                       13);
    printf("%lld\n", x);
  }
}