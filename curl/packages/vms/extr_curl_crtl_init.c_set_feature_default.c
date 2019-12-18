__attribute__((used)) static void set_feature_default(const char *name, int value)
{
    int index;

    index = decc$feature_get_index(name);

    if (index > 0)
        decc$feature_set_value (index, 0, value);
}