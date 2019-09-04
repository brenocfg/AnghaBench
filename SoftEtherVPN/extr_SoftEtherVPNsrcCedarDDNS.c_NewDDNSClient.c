#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_8__ {int /*<<< orphan*/  ref; } ;
struct TYPE_7__ {int /*<<< orphan*/  Thread; int /*<<< orphan*/  Event; int /*<<< orphan*/  Lock; int /*<<< orphan*/  InternetSetting; int /*<<< orphan*/ * Key; int /*<<< orphan*/  Err_IPv6; int /*<<< orphan*/  Err_IPv4; TYPE_2__* Cedar; } ;
typedef  int /*<<< orphan*/  INTERNET_SETTING ;
typedef  TYPE_1__ DDNS_CLIENT ;
typedef  TYPE_2__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  DCGenNewKey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DCThread ; 
 int /*<<< orphan*/  ERR_TRYING_TO_CONNECT ; 
 int /*<<< orphan*/  NewEvent () ; 
 int /*<<< orphan*/  NewLock () ; 
 int /*<<< orphan*/  NewThread (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  Sha1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* ZeroMalloc (int) ; 

DDNS_CLIENT *NewDDNSClient(CEDAR *cedar, UCHAR *key, INTERNET_SETTING *t)
{
	DDNS_CLIENT *c;
	UCHAR key_hash[SHA1_SIZE];
	// Validate arguments
	if (cedar == NULL)
	{
		return NULL;
	}

	c = ZeroMalloc(sizeof(DDNS_CLIENT));
	c->Cedar = cedar;
	AddRef(c->Cedar->ref);

	c->Err_IPv4 = c->Err_IPv6 = ERR_TRYING_TO_CONNECT;

	if (key == NULL)
	{
		// Create a new key
		DCGenNewKey(c->Key);
	}
	else
	{
		// Set the key
		Copy(c->Key, key, SHA1_SIZE);
	}

	Sha1(key_hash, c->Key, sizeof(c->Key));


	if (t != NULL)
	{
		Copy(&c->InternetSetting, t, sizeof(INTERNET_SETTING));
	}

	c->Lock = NewLock();

	// Thread creation
	c->Event = NewEvent();
	c->Thread = NewThread(DCThread, c);

	return c;
}