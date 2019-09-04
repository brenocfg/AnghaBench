#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* name; } ;
typedef  TYPE_1__ content_encoding ;

/* Variables and functions */
 int /*<<< orphan*/  CONTENT_ENCODING_DEFAULT ; 
 TYPE_1__** encodings ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  strcasecompare (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 

char *Curl_all_content_encodings(void)
{
  size_t len = 0;
  const content_encoding * const *cep;
  const content_encoding *ce;
  char *ace;

  for(cep = encodings; *cep; cep++) {
    ce = *cep;
    if(!strcasecompare(ce->name, CONTENT_ENCODING_DEFAULT))
      len += strlen(ce->name) + 2;
  }

  if(!len)
    return strdup(CONTENT_ENCODING_DEFAULT);

  ace = malloc(len);
  if(ace) {
    char *p = ace;
    for(cep = encodings; *cep; cep++) {
      ce = *cep;
      if(!strcasecompare(ce->name, CONTENT_ENCODING_DEFAULT)) {
        strcpy(p, ce->name);
        p += strlen(p);
        *p++ = ',';
        *p++ = ' ';
      }
    }
    p[-2] = '\0';
  }

  return ace;
}