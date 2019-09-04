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
typedef  int /*<<< orphan*/  user_addr_t ;
struct persona {int /*<<< orphan*/  pna_id; } ;

/* Variables and functions */
 int ESRCH ; 
 int copyout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct persona* current_persona_get () ; 
 int /*<<< orphan*/  persona_put (struct persona*) ; 

__attribute__((used)) static int kpersona_get_syscall(user_addr_t idp)
{
	int error;
	struct persona *persona = current_persona_get();

	if (!persona)
		return ESRCH;

	error = copyout(&persona->pna_id, idp, sizeof(persona->pna_id));
	persona_put(persona);

	return error;
}