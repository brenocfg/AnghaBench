__attribute__((used)) static void test_string() {
    char s[] = "abc";
    expect_string("abc", s);
    char t[] = { "def" };
    expect_string("def", t);
}