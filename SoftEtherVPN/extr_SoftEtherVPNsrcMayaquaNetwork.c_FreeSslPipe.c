#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ssl_ctx; int /*<<< orphan*/  ssl; int /*<<< orphan*/  RawOut; int /*<<< orphan*/  RawIn; int /*<<< orphan*/  SslInOut; } ;
typedef  TYPE_1__ SSL_PIPE ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeSslBio (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ ) ; 

void FreeSslPipe(SSL_PIPE *s)
{
	// Validate arguments
	if (s == NULL)
	{
		return;
	}

	FreeSslBio(s->SslInOut);
	FreeSslBio(s->RawIn);
	FreeSslBio(s->RawOut);

	SSL_free(s->ssl);
	SSL_CTX_free(s->ssl_ctx);

	Free(s);
}