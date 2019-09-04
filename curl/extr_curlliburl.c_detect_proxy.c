#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct connectdata {int /*<<< orphan*/  data; TYPE_1__* handler; } ;
typedef  int /*<<< orphan*/  proxy_env ;
struct TYPE_2__ {char* scheme; } ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_strntoupper (char*,char*,int) ; 
 char* curl_getenv (char*) ; 
 int /*<<< orphan*/  infof (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  strcasecompare (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ tolower (int) ; 

__attribute__((used)) static char *detect_proxy(struct connectdata *conn)
{
  char *proxy = NULL;

  /* If proxy was not specified, we check for default proxy environment
   * variables, to enable i.e Lynx compliance:
   *
   * http_proxy=http://some.server.dom:port/
   * https_proxy=http://some.server.dom:port/
   * ftp_proxy=http://some.server.dom:port/
   * no_proxy=domain1.dom,host.domain2.dom
   *   (a comma-separated list of hosts which should
   *   not be proxied, or an asterisk to override
   *   all proxy variables)
   * all_proxy=http://some.server.dom:port/
   *   (seems to exist for the CERN www lib. Probably
   *   the first to check for.)
   *
   * For compatibility, the all-uppercase versions of these variables are
   * checked if the lowercase versions don't exist.
   */
  char proxy_env[128];
  const char *protop = conn->handler->scheme;
  char *envp = proxy_env;
  char *prox;

  /* Now, build <protocol>_proxy and check for such a one to use */
  while(*protop)
    *envp++ = (char)tolower((int)*protop++);

  /* append _proxy */
  strcpy(envp, "_proxy");

  /* read the protocol proxy: */
  prox = curl_getenv(proxy_env);

  /*
   * We don't try the uppercase version of HTTP_PROXY because of
   * security reasons:
   *
   * When curl is used in a webserver application
   * environment (cgi or php), this environment variable can
   * be controlled by the web server user by setting the
   * http header 'Proxy:' to some value.
   *
   * This can cause 'internal' http/ftp requests to be
   * arbitrarily redirected by any external attacker.
   */
  if(!prox && !strcasecompare("http_proxy", proxy_env)) {
    /* There was no lowercase variable, try the uppercase version: */
    Curl_strntoupper(proxy_env, proxy_env, sizeof(proxy_env));
    prox = curl_getenv(proxy_env);
  }

  envp = proxy_env;
  if(prox) {
    proxy = prox; /* use this */
  }
  else {
    envp = (char *)"all_proxy";
    proxy = curl_getenv(envp); /* default proxy to use */
    if(!proxy) {
      envp = (char *)"ALL_PROXY";
      proxy = curl_getenv(envp);
    }
  }
  if(proxy)
    infof(conn->data, "Uses proxy env variable %s == '%s'\n", envp, proxy);

  return proxy;
}