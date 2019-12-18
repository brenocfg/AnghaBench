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
typedef  size_t UINT ;
struct TYPE_8__ {size_t CryptoId; char* Name; size_t* KeySizes; int VariableKeySize; size_t BlockSize; } ;
struct TYPE_7__ {int /*<<< orphan*/  CryptosList; } ;
typedef  TYPE_1__ IKE_ENGINE ;
typedef  TYPE_2__ IKE_CRYPTO ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ ,TYPE_2__*) ; 
 size_t MIN (size_t,int) ; 
 TYPE_2__* ZeroMalloc (int) ; 

IKE_CRYPTO *NewIkeCrypto(IKE_ENGINE *e, UINT crypto_id, char *name, UINT *key_sizes, UINT num_key_sizes, UINT block_size)
{
	IKE_CRYPTO *c;
	UINT i;
	// Validate arguments
	if (e == NULL || name == NULL || key_sizes == NULL)
	{
		return NULL;
	}

	c = ZeroMalloc(sizeof(IKE_CRYPTO));

	c->CryptoId = crypto_id;
	c->Name = name;

	for (i = 0;i < MIN(num_key_sizes, 16);i++)
	{
		c->KeySizes[i] = key_sizes[i];
	}

	if (num_key_sizes >= 2)
	{
		c->VariableKeySize = true;
	}

	c->BlockSize = block_size;

	Add(e->CryptosList, c);

	return c;
}