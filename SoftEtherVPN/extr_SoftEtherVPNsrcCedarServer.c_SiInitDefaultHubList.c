#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  o ;
struct TYPE_13__ {int Bridge; } ;
struct TYPE_12__ {int Offline; int /*<<< orphan*/  SecurePassword; int /*<<< orphan*/  HashedPassword; int /*<<< orphan*/  CreatedTime; } ;
struct TYPE_11__ {TYPE_8__* Cedar; } ;
typedef  TYPE_1__ SERVER ;
typedef  int /*<<< orphan*/  HUB_OPTION ;
typedef  int /*<<< orphan*/  HUB_LOG ;
typedef  TYPE_2__ HUB ;

/* Variables and functions */
 int /*<<< orphan*/  AddHub (TYPE_8__*,TYPE_2__*) ; 
 TYPE_2__* NewHub (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Rand (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ReleaseHub (TYPE_2__*) ; 
 int /*<<< orphan*/  SERVER_DEFAULT_BRIDGE_NAME ; 
 int /*<<< orphan*/  SERVER_DEFAULT_HUB_NAME ; 
 int /*<<< orphan*/  SetHubLogSetting (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetHubOnline (TYPE_2__*) ; 
 int /*<<< orphan*/  SiSetDefaultHubOption (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SiSetDefaultLogSetting (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SystemTime64 () ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 

void SiInitDefaultHubList(SERVER *s)
{
	HUB *h;
	HUB_OPTION o;
	HUB_LOG g;
	// Validate arguments
	if (s == NULL)
	{
		return;
	}

	Zero(&o, sizeof(o));

	// Configure a default Virtual HUB management options
	SiSetDefaultHubOption(&o);

	h = NewHub(s->Cedar, s->Cedar->Bridge == false ? SERVER_DEFAULT_HUB_NAME : SERVER_DEFAULT_BRIDGE_NAME, &o);
	h->CreatedTime = SystemTime64();
	AddHub(s->Cedar, h);

	if (s->Cedar->Bridge)
	{
		// Randomize the password
		Rand(h->HashedPassword, sizeof(h->HashedPassword));
		Rand(h->SecurePassword, sizeof(h->SecurePassword));
	}

	h->Offline = true;
	SetHubOnline(h);

	// Log settings
	SiSetDefaultLogSetting(&g);
	SetHubLogSetting(h, &g);

	ReleaseHub(h);
}