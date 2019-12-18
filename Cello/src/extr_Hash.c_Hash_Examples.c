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
struct Example {char* member_0; char* member_1; } ;

/* Variables and functions */

__attribute__((used)) static struct Example* Hash_Examples(void) {
  
  static struct Example examples[] = {
    {
      "Usage",
      "println(\"%li\", $I(hash($I(  1)))); /*   1 */\n"
      "println(\"%li\", $I(hash($I(123)))); /* 123 */\n"
      "\n"
      "/* 866003103 */\n"
      "println(\"%li\", $I(hash_data($I(123), size(Int))));\n"
      "\n"
      "println(\"%li\", $I(hash($S(\"Hello\"))));  /* -1838682532 */\n"
      "println(\"%li\", $I(hash($S(\"There\"))));  /*   961387266 */\n"
      "println(\"%li\", $I(hash($S(\"People\")))); /*   697467069 */\n"
    }, {NULL, NULL}
  };

  return examples;
  
}