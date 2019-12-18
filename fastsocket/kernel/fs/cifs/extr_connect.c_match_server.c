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
struct sockaddr {int dummy; } ;
struct smb_vol {int /*<<< orphan*/  srcaddr; } ;
struct TCP_Server_Info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  match_address (struct TCP_Server_Info*,struct sockaddr*,struct sockaddr*) ; 
 int /*<<< orphan*/  match_port (struct TCP_Server_Info*,struct sockaddr*) ; 
 int /*<<< orphan*/  match_security (struct TCP_Server_Info*,struct smb_vol*) ; 

__attribute__((used)) static int match_server(struct TCP_Server_Info *server, struct sockaddr *addr,
			 struct smb_vol *vol)
{
	if (!match_address(server, addr,
			   (struct sockaddr *)&vol->srcaddr))
		return 0;

	if (!match_port(server, addr))
		return 0;

	if (!match_security(server, vol))
		return 0;

	return 1;
}