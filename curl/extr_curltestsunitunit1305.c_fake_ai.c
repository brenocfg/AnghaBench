#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in {int dummy; } ;
struct TYPE_5__ {int ai_addrlen; int /*<<< orphan*/  ai_family; struct TYPE_5__* ai_canonname; void* ai_addr; } ;
typedef  TYPE_1__ Curl_addrinfo ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* strdup (char*) ; 

__attribute__((used)) static Curl_addrinfo *fake_ai(void)
{
  static Curl_addrinfo *ai;

  ai = calloc(1, sizeof(Curl_addrinfo));
  if(!ai)
    return NULL;

  ai->ai_canonname = strdup("dummy");
  if(!ai->ai_canonname) {
    free(ai);
    return NULL;
  }

  ai->ai_addr = calloc(1, sizeof(struct sockaddr_in));
  if(!ai->ai_addr) {
    free(ai->ai_canonname);
    free(ai);
    return NULL;
  }

  ai->ai_family = AF_INET;
  ai->ai_addrlen = sizeof(struct sockaddr_in);

  return ai;
}