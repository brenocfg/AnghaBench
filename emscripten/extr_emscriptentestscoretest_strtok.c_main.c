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
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 char* strtok_r (char*,char const*,char**) ; 

int main() {
  char test[80], blah[80];
  const char *sep = "\\/:;=-";
  char *word, *phrase, *brkt, *brkb;

  strcpy(test, "This;is.a:test:of=the/string\\tokenizer-function.");

  for (word = strtok_r(test, sep, &brkt); word;
       word = strtok_r(NULL, sep, &brkt)) {
    strcpy(blah, "blah:blat:blab:blag");
    for (phrase = strtok_r(blah, sep, &brkb); phrase;
         phrase = strtok_r(NULL, sep, &brkb)) {
      printf("at %s:%s\n", word, phrase);
    }
  }
  return 0;
}