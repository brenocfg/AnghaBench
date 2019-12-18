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
struct KEY_STACK {struct KEYS* element; struct KEY_STACK* next; } ;
struct KEYS {char* string; int length; void* value; } ;

/* Variables and functions */
 int K1__ ; 
 int K5__ ; 
 struct KEY_STACK* KEY_TOS ; 
 void** Key_vals ; 
 int Max_Key_len ; 
 char** String_table ; 
 int kUND__ ; 
 int kb__ ; 
 int kbeg__ ; 
 int kcbt__ ; 
 int ke__ ; 
 int kf11__ ; 
 int kf63__ ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 void* strlen (char*) ; 

void 
Key_Get()		/* create linked list with all key sequences obtained from terminal database	*/
{
	int Counter;
	int Klen;
	int key_def;
	struct KEY_STACK *Spoint;

	Max_Key_len = 0;
	Counter = 0;
	key_def = kb__;
	while (key_def <= kf63__)
	{
		if (key_def == ke__)
			key_def = K1__;
		else if (key_def == (K5__ + 1))
			key_def = kcbt__;
		else if (key_def == (kcbt__ + 1))
			key_def = kbeg__;
		else if (key_def == (kUND__ + 1))
			key_def = kf11__;
		if (String_table[key_def] != NULL)
		{
			if (KEY_TOS == NULL)
				Spoint = KEY_TOS = (struct KEY_STACK *) malloc(sizeof(struct KEY_STACK));
			else
			{
				Spoint = KEY_TOS;
				while (Spoint->next != NULL)
					Spoint = Spoint->next;
				Spoint->next = (struct KEY_STACK *) malloc(sizeof(struct KEY_STACK));
				Spoint = Spoint->next;
			}
			Spoint->next = NULL;
			Spoint->element = (struct KEYS *) malloc(sizeof(struct KEYS));
			Spoint->element->string = String_table[key_def];
			Spoint->element->length = strlen(String_table[key_def]);
			Spoint->element->value = Key_vals[Counter];
			Klen = strlen(Spoint->element->string);
			if (Klen > Max_Key_len)
				Max_Key_len = Klen;
			/*
			 |  Some terminal types accept keystrokes of the form
			 |  \E[A and \EOA, substituting '[' for 'O'.  Make a 
			 |  duplicate of such key strings (since the 
			 |  database will only have one version) so new_curse 
			 |  can understand both.
			 */
			if ((Spoint->element->length > 1) && 
			    ((String_table[key_def][1] == '[') || 
			     (String_table[key_def][1] == 'O')))
			{
				Spoint->next = (struct KEY_STACK *) malloc(sizeof(struct KEY_STACK));
				Spoint = Spoint->next;
				Spoint->next = NULL;
				Spoint->element = (struct KEYS *) malloc(sizeof(struct KEYS));
				Spoint->element->length = strlen(String_table[key_def]);
				Spoint->element->string = malloc(Spoint->element->length + 1);
				strcpy(Spoint->element->string, String_table[key_def]);
				Spoint->element->value = Key_vals[Counter];
				Klen = strlen(Spoint->element->string);
				if (Klen > Max_Key_len)
					Max_Key_len = Klen;
			
				if (String_table[key_def][1] == '[')
					Spoint->element->string[1] = 'O';
				else
					Spoint->element->string[1] = '[';
			}
		}
		key_def++;
		Counter++;
	}
}