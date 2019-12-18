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
typedef  int /*<<< orphan*/  u8 ;
struct orinoco_private {TYPE_1__* keys; } ;
typedef  enum orinoco_alg { ____Placeholder_orinoco_alg } orinoco_alg ;
struct TYPE_2__ {int key_len; int seq_len; scalar_t__ cipher; int /*<<< orphan*/ * key; int /*<<< orphan*/ * seq; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
#define  ORINOCO_ALG_NONE 130 
#define  ORINOCO_ALG_TKIP 129 
#define  ORINOCO_ALG_WEP 128 
 int SMALL_KEY_SIZE ; 
 scalar_t__ WLAN_CIPHER_SUITE_TKIP ; 
 scalar_t__ WLAN_CIPHER_SUITE_WEP104 ; 
 scalar_t__ WLAN_CIPHER_SUITE_WEP40 ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int orinoco_set_key(struct orinoco_private *priv, int index,
			   enum orinoco_alg alg, const u8 *key, int key_len,
			   const u8 *seq, int seq_len)
{
	kzfree(priv->keys[index].key);
	kzfree(priv->keys[index].seq);

	if (key_len) {
		priv->keys[index].key = kzalloc(key_len, GFP_ATOMIC);
		if (!priv->keys[index].key)
			goto nomem;
	} else
		priv->keys[index].key = NULL;

	if (seq_len) {
		priv->keys[index].seq = kzalloc(seq_len, GFP_ATOMIC);
		if (!priv->keys[index].seq)
			goto free_key;
	} else
		priv->keys[index].seq = NULL;

	priv->keys[index].key_len = key_len;
	priv->keys[index].seq_len = seq_len;

	if (key_len)
		memcpy(priv->keys[index].key, key, key_len);
	if (seq_len)
		memcpy(priv->keys[index].seq, seq, seq_len);

	switch (alg) {
	case ORINOCO_ALG_TKIP:
		priv->keys[index].cipher = WLAN_CIPHER_SUITE_TKIP;
		break;

	case ORINOCO_ALG_WEP:
		priv->keys[index].cipher = (key_len > SMALL_KEY_SIZE) ?
			WLAN_CIPHER_SUITE_WEP104 : WLAN_CIPHER_SUITE_WEP40;
		break;

	case ORINOCO_ALG_NONE:
	default:
		priv->keys[index].cipher = 0;
		break;
	}

	return 0;

free_key:
	kfree(priv->keys[index].key);
	priv->keys[index].key = NULL;

nomem:
	priv->keys[index].key_len = 0;
	priv->keys[index].seq_len = 0;
	priv->keys[index].cipher = 0;

	return -ENOMEM;
}