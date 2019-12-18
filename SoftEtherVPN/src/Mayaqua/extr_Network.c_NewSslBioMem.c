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
struct TYPE_4__ {void* SendFifo; void* RecvFifo; int /*<<< orphan*/  bio; } ;
typedef  TYPE_1__ SSL_BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_s_mem () ; 
 void* NewFifo () ; 
 TYPE_1__* ZeroMalloc (int) ; 

SSL_BIO *NewSslBioMem()
{
	SSL_BIO *b = ZeroMalloc(sizeof(SSL_BIO));

	b->bio = BIO_new(BIO_s_mem());

	b->RecvFifo = NewFifo();
	b->SendFifo = NewFifo();

	return b;
}