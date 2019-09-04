#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_7__ {int size; } ;
struct TYPE_6__ {int IsDisconnected; int /*<<< orphan*/  RecvFifo; int /*<<< orphan*/  bio; TYPE_3__* SendFifo; } ;
typedef  TYPE_1__ SSL_BIO ;

/* Variables and functions */
 int BIO_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ BIO_should_retry (int /*<<< orphan*/ ) ; 
 int BIO_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_peek_last_error () ; 
 int /*<<< orphan*/  FifoSize (TYPE_3__*) ; 
 int /*<<< orphan*/  GetFifoPointer (TYPE_3__*) ; 
 int /*<<< orphan*/  ReadFifo (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WHERE ; 
 int /*<<< orphan*/  WriteFifo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

bool SslBioSync(SSL_BIO *b, bool sync_send, bool sync_recv)
{
	// Validate arguments
	if (b == NULL)
	{
		return false;
	}

	if (b->IsDisconnected)
	{
		return false;
	}

	// Write the contents of the SendFifo to the BIO
	if (sync_send)
	{
		while (b->SendFifo->size >= 1)
		{
			int r = BIO_write(b->bio, GetFifoPointer(b->SendFifo), FifoSize(b->SendFifo));

			if (r == 0)
			{
				b->IsDisconnected = true;
				WHERE;
				return false;
			}
			else
			{
				if (r < 0)
				{
					if (BIO_should_retry(b->bio))
					{
						break;
					}
					else
					{
						b->IsDisconnected = true;
						WHERE;
						return false;
					}
				}
				else
				{
					ReadFifo(b->SendFifo, NULL, (UINT)r);
				}
			}
		}
	}

	// Save to the RecvFifo by reading from the BIO
	if (sync_recv)
	{
		while (true)
		{
			UCHAR tmp[4096];
			int r;

			r = BIO_read(b->bio, tmp, sizeof(tmp));

			if (r == 0)
			{
				b->IsDisconnected = true;
				WHERE;
				return false;
			}
			else
			{
				if (r < 0)
				{
					if (BIO_should_retry(b->bio))
					{
						break;
					}
					else
					{
						b->IsDisconnected = true;
						WHERE;
						Debug("OpenSSL Error: %s\n", ERR_error_string(ERR_peek_last_error(), NULL));
						return false;
					}
				}
				else
				{
					WriteFifo(b->RecvFifo, tmp, (UINT)r);
				}
			}
		}
	}

	return true;
}