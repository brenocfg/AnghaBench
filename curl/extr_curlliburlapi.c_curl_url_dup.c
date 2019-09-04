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
struct Curl_URL {int /*<<< orphan*/  portnum; } ;
typedef  struct Curl_URL CURLU ;

/* Variables and functions */
 int /*<<< orphan*/  DUP (struct Curl_URL*,struct Curl_URL*,int /*<<< orphan*/ ) ; 
 struct Curl_URL* calloc (int,int) ; 
 int /*<<< orphan*/  curl_url_cleanup (struct Curl_URL*) ; 
 int /*<<< orphan*/  fragment ; 
 int /*<<< orphan*/  host ; 
 int /*<<< orphan*/  options ; 
 int /*<<< orphan*/  password ; 
 int /*<<< orphan*/  path ; 
 int /*<<< orphan*/  port ; 
 int /*<<< orphan*/  query ; 
 int /*<<< orphan*/  scheme ; 
 int /*<<< orphan*/  user ; 

CURLU *curl_url_dup(CURLU *in)
{
  struct Curl_URL *u = calloc(sizeof(struct Curl_URL), 1);
  if(u) {
    DUP(u, in, scheme);
    DUP(u, in, user);
    DUP(u, in, password);
    DUP(u, in, options);
    DUP(u, in, host);
    DUP(u, in, port);
    DUP(u, in, path);
    DUP(u, in, query);
    DUP(u, in, fragment);
    u->portnum = in->portnum;
  }
  return u;
  fail:
  curl_url_cleanup(u);
  return NULL;
}