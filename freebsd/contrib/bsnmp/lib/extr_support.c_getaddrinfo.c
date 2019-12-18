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
struct sockaddr_in {scalar_t__ sin_family; int sin_len; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; } ;
struct servent {int /*<<< orphan*/  s_port; } ;
struct hostent {scalar_t__ h_addrtype; int /*<<< orphan*/  h_addr; } ;
struct addrinfo {scalar_t__ ai_family; int ai_addrlen; int /*<<< orphan*/ * ai_addr; int /*<<< orphan*/ * ai_next; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_flags; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int HOST_NOT_FOUND ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 struct hostent* gethostbyname (char const*) ; 
 struct servent* getservbyname (char const*,int /*<<< orphan*/ *) ; 
 int h_errno ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int
getaddrinfo(const char *host, const char *port, const struct addrinfo *hints,
    struct addrinfo **res)
{
	struct hostent *hent;
	struct sockaddr_in *s;
	struct servent *sent;

	if ((hent = gethostbyname(host)) == NULL)
		return (h_errno);
	if (hent->h_addrtype != hints->ai_family)
		return (HOST_NOT_FOUND);
	if (hent->h_addrtype != AF_INET)
		return (HOST_NOT_FOUND);

	if ((*res = malloc(sizeof(**res))) == NULL)
		return (HOST_NOT_FOUND);

	(*res)->ai_flags = hints->ai_flags;
	(*res)->ai_family = hints->ai_family;
	(*res)->ai_socktype = hints->ai_socktype;
	(*res)->ai_protocol = hints->ai_protocol;
	(*res)->ai_next = NULL;

	if (((*res)->ai_addr = malloc(sizeof(struct sockaddr_in))) == NULL) {
		freeaddrinfo(*res);
		return (HOST_NOT_FOUND);
	}
	(*res)->ai_addrlen = sizeof(struct sockaddr_in);
	s = (struct sockaddr_in *)(*res)->ai_addr;
	s->sin_family = hints->ai_family;
	s->sin_len = sizeof(*s);
	memcpy(&s->sin_addr, hent->h_addr, 4);

	if ((sent = getservbyname(port, NULL)) == NULL) {
		freeaddrinfo(*res);
		return (HOST_NOT_FOUND);
	}
	s->sin_port = sent->s_port;

	return (0);
}